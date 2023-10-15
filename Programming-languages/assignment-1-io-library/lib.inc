%define SYS_EXIT 60
%define SYS_WRITE 1
%define FD_STDOUT 1
%define ASCII_OFFSET 0x30
section .text


; Принимает код возврата и завершает текущий процесс
exit:
        mov     rax, SYS_EXIT
        xor     rdi, rdi        ; error code
        syscall


; Принимает указатель на нуль-терминированную строку, возвращает её длину
string_length:
        mov     rax, -1
.loop:
        inc     rax
        cmp     byte[rdi+rax], 0
        jne     .loop
        ret

; Выводит беззнаковое 8-байтовое число в десятичном формате
; Совет: выделите место в стеке и храните там результаты деления
; Не забудьте перевести цифры в их ASCII коды.
print_uint:
        mov     r10, 10         ; decimal number base system
        mov     rax, rdi        ; 8-bytes number
        mov     r8, rsp         ; save stack pointer
        dec     rsp
        mov     byte[rsp], 0    ; push stop symbol

.loop:
        xor     rdx, rdx
        div     r10                     ; rax - Quotient, rdx - Remainder
        add     rdx, ASCII_OFFSET       ; ASCII offset
        dec     rsp                     ; step back in stack
        mov     byte[rsp], dl
        cmp     rax, 0
        ja      .loop
.end:
        mov     rdi, rsp
        call    print_string
        mov     rsp, r8         ; restore stack pointer
        ret

; Принимает указатель на нуль-терминированную строку, выводит её в stdout
print_string:
        mov     rsi, rdi
        call    string_length
        mov     rdx, rax
        mov     rax, SYS_WRITE
        mov     rdi, FD_STDOUT
        syscall
        ret

; Переводит строку (выводит символ с кодом 0xA)
print_newline:
        xor     rax, rax
        mov     rdi, '\n'
; Принимает код символа и выводит его в stdout
print_char:
        push    rdi
        mov     rsi, rsp
        pop     rdi
        mov     rax, SYS_WRITE
        mov     rdi, FD_STDOUT
        mov     rdx, 1          ; byte count
        syscall
        ret

; Выводит знаковое 8-байтовое число в десятичном формате
print_int:
        cmp     rdi, 0
        jge     .print
        neg     rdi
        push    rdi
        mov     rdi, '-'       ; 0x2D == 45 == '-'
        call    print_char
        pop     rdi
.print:
        jmp    print_uint
        
; Принимает два указателя на нуль-терминированные строки, возвращает 1 если они равны, 0 иначе
string_equals:
        xor     rcx, rcx
        xor     rax, rax
        xor     r9, r9
        push    rdi
        mov     r9, rdi
        mov     rdi, rsi
        call    string_length
        mov     r8, rax
        mov     rdi, r9
        call    string_length
        pop     rdi
        cmp     rax, r8
        jne     .noeq
.loop:
        mov     r8b, byte[rdi+rcx]
        mov     r9b, byte[rsi+rcx]
        cmp     r8b, r9b
        jne     .noeq
        inc     rcx
        cmp     r8b, 0
        jnz     .loop
.eq:
        mov     rax, 1
        ret
.noeq:
        mov     rax, 0
        ret
; Читает один символ из stdin и возвращает его. Возвращает 0 если достигнут конец потока
read_char:
        xor     rax, rax        ; sys_read
        xor     rdi, rdi        ; fd stdin
        push    0               ; end stream symbol
        mov     rdx, 1          ; byte to read
        mov     rsi, rsp
        syscall
        pop     rax
        ret

; Принимает: адрес начала буфера, размер буфера
; Читает в буфер слово из stdin, пропуская пробельные символы в начале, .
; Пробельные символы это пробел 0x20, табуляция 0x9 и перевод строки 0xA.
; Останавливается и возвращает 0 если слово слишком большое для буфера
; При успехе возвращает адрес буфера в rax, длину слова в rdx.
; При неудаче возвращает 0 в rax
; Эта функция должна дописывать к слову нуль-терминатор
read_word:
        sub     rsi, 1
        xor     rax, rax
        xor     rdx, rdx
        xor     rcx, rcx
.loop:
        push    rcx
        push    rdi
        push    rsi
        push    rdx
        call    read_char
        pop     rdx
        pop     rsi
        pop     rdi
        pop     rcx
        cmp     rax, 0
        je      .end
        cmp     rax, ' '
        je      .skip
        cmp     rax, 0x9
        je      .skip
        cmp     rax, '\n'
        je      .skip
.cont:
        mov     [rdi+rcx], rax
        inc     rcx
        cmp     rcx, rsi
        jle     .loop
.error:
        xor     rax, rax
        xor     rdx, rdx
        ret
.skip:
        cmp     rcx, 0
        je      .loop
.end:
        xor     rax, rax
        mov     [rdi+rcx+1], rax
        mov     rax, rdi
        mov     rdx, rcx
        ret
; Принимает указатель на строку, пытается
; прочитать из её начала беззнаковое число.
; Возвращает в rax: число, rdx : его длину в символах
; rdx = 0 если число прочитать не удалось
parse_uint:
        xor     rax, rax
        xor     rcx, rcx
        xor     r8, r8
        mov     r10, 10
.loop:
        mov     r8b, byte[rdi+rcx]
        cmp     r8b, 0x30                       ; > 0
        jb      .end
        cmp     r8b, 0x39                       ; < 9
        ja      .end
        sub     r8b, ASCII_OFFSET               ;ASCII offset
        mul     r10
        add     rax, r8
        inc     rcx
        jmp     .loop

.end:
        mov     rdx, rcx
        ret

; Принимает указатель на строку, пытается
; прочитать из её начала знаковое число.
; Если есть знак, пробелы между ним и числом не разрешены.
; Возвращает в rax: число, rdx : его длину в символах (включая знак, если он был)
; rdx = 0 если число прочитать не удалось
parse_int:
        xor     rax, rax
        mov     r8b, byte[rdi]
        cmp     r8b, '-'               ; check '-'
        jne     parse_uint
        inc     rdi
        call    parse_uint
        neg     rax
        inc     rdx
        ret

; Принимает указатель на строку, указатель на буфер и длину буфера
; Копирует строку в буфер
; Возвращает длину строки если она умещается в буфер, иначе 0
string_copy:
        push    rdi
        push    rsi
        push    rdx
        call    string_length
        pop     rdx
        pop     rsi
        pop     rdi
        cmp     rax, rdx
        ja      .error
        cmp     rdx, 0
        je      .error
        xor     rcx, rcx
.loop:
        cmp     rcx, rax
        jg      .end
        mov     r9, [rdi+rcx]
        mov     [rsi+rcx], r9
        inc     rcx
        jmp     .loop
.end:
        mov     rax, rcx
        ret
.error:
        xor     rax, rax
        ret
                    