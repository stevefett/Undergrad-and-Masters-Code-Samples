title ASM template(template.asm)

; This is a program template.
.model small
.stack 100h
.data 
	Year DW 0
	R2D2 DW ?
	String DB "R2D2 = "
		d1 DB 0
		d2 DB 0
		d3 DB 0
		d4 DB 0
		d5 DB 0
		DB '$'
	temp DW ?
	Ask DB "Enter Year (will not echo):",0dh, 0ah, "$" 



.code
main proc
	mov ax,@data
	mov ds,ax

;Takes the year as character input
	mov ah, 9               
	mov dx, OFFSET Ask 

	int 21h

	call getInt
	call mathWork
	mov R2D2, cx
	call printVal


	mov ax,4c00h
	int 21h

main endp

getCh PROC
	mov ah, 7
	int 21h
	ret
getCh ENDP

getInt PROC
	mov cx,0
	mov dx,0
	call getCh


	LOOPSTART:
		
		cmp al, 29h
		jle LOOPEND
		cmp al, 40h
		jge LOOPEND
		cmp al, 0dh
		je LOOPEND

		sub al, 30h
		mov dl, al

		mov ax, cx
		mov cx, dx
		mov dx, 0
		mov bx, 10d
		imul bx
		add cx, ax

		call getCh
		jmp LOOPSTART
	LOOPEND:
	ret

getInt ENDP

mathWork PROC
	mov dx, 0
;Increments the year
 	inc cx                   ;ax = 2005  (07D5h)
	mov ax, cx

;Multiplies year times 3
	mov bx, 3
	imul bx                  ;ax = 2005 * 3 = 6015 (117Fh)
	
;mod Year*3 by 7 
	mov bx, 7
	idiv bx                  ;ax = 859 (035Bh)  dx = 2(h)
	
;Does the math to R2D2           
	add cx, 36               ;cx = 36 (0024h)
	sub cx, 2000             ;cx = 41 (0029h)
	add cx, dx               ;cx = 41 + 2 = 43 (002Bh)                	          

	ret

mathWork ENDP

printVal PROC
	mov ax, R2D2             ;this puts 04h in AX, 03h in DX
	mov dx, 0                
	mov bx, 10
	idiv bx

	mov d5, dl             ;converts dx's 04 to ascii 
	or d5, 30h
	cwd
	idiv bx

	mov d4, dl             ;converts dx's 04 to ascii 
	or d4, 30h
	cwd
	idiv bx

	mov d3, dl
	or d3, 30h
	cwd
	idiv bx

	mov d2, dl
	or d2, 30h
	cwd
	idiv bx
	mov d1, dl
	or d1, 30h

	cmp d1, 30h
	jne skip

	mov d1, 0
	cmp d2, 30h
	jne skip
	mov d2, 0
	cmp d3, 30h
	jne skip
	mov d3, 0
	jne skip 
	cmp d4, 30h
	jne skip
	mov d4,0

skip:
	mov ah, 09h
	mov dx, offset String
	int 21h

	ret

printVal ENDP

end main
