%macro load_sepia_mult 0
    movups xmm3, [blue_sepia]
    movups xmm4, [green_sepia]
    movups xmm5, [red_sepia]
    movups xmm6, [max_value]
%endmacro
%macro process_pixel 3
    xor rcx, rcx
    mov cl, byte[%1]
    pxor %2, %2
    pinsrb %2, ecx, 0
    pinsrb %2, ecx, 4
    pinsrb %2, ecx, 8
    cvtdq2ps %2, %2
    mulps %2, %3
%endmacro
section .rodata
    align 16
    red_sepia dd 0.393, 0.349, 0.272, 0
    align 16
    green_sepia dd 0.769, 0.686, 0.534, 0
    align 16
    blue_sepia dd 0.189, 0.168, 0.131, 0
    align 16
    max_value dd 255, 255, 255, 0
section .text
;Serpia filter using SSE
global sepia_filter_asm
sepia_filter_asm:
    mov rax, [rdi+16] ; rax - current pixel
    xor r8, r8
    mov r8, [rdi]	; width
    imul r8, [rdi+8]	; width*height
    imul r8, 3		; width*height*3 (3 - bytes per pixel)
    add r8, rax ; r8 - max address
    load_sepia_mult
    .loop:
            process_pixel rax, xmm0, xmm3
            process_pixel rax+1, xmm1, xmm4
            process_pixel rax+2, xmm2, xmm5
            addps xmm0, xmm1
            addps xmm0, xmm2
            cvtps2dq xmm0, xmm0
            pminud xmm0, xmm6

            pextrb byte [rax + 2], xmm0, 0
            pextrb byte [rax + 1], xmm0, 4
            pextrb byte [rax], xmm0, 8

            add rax, 3
            cmp rax, r8
    jl .loop
    ret



