title ASM template(template.asm)

; This is a program template.
.model small
.stack 100h
.data 
	Year DW 2004
	R2D2 DW ?
.code
main proc
	mov ax,@data
	mov ds,ax

;Increments the year
	mov ax,Year              ;ax = 2004  (07D4h)
	inc ax                   ;ax = 2005  (07D5h)
	mov Year, ax

;Multiplies year times 3
	mov bx, 3
	imul bx                  ;ax = 2005 * 3 = 6015 (117Fh)
	
;mod Year*3 by 7 
	mov bx, 7
	idiv bx                  ;ax = 859 (035Bh)  dx = 2(h)
	
;Does the math to R2D2
	mov cx, R2D2             
	mov cx, 36               ;cx = 36 (0024h)
	add cx, Year             ;cx = 2005 + 36 = 2041 (07F9h)
	sub cx, 2000             ;cx = 41 (0029h)
	add cx, dx               ;cx = 41 + 2 = 43 (002Bh)                
	mov R2D2, cx	          

;Ends Program
	mov ax,4c00h
	int 21h
main endp
end main