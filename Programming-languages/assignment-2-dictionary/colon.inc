%macro colon 2
%ifdef NEXT	
%else
	%define	NEXT 0
%endif
%ifstr %1
%else
	%error "Key must be a string"
%endif
%ifid %2
%else
	%error "Incorrect name for the label"
%endif

%2:
	dq NEXT
	db %1, 0

%define NEXT %2
%endmacro
