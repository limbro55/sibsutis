.global main

main:
  movl $0xaf, %eax
  mov $512, %rbx
  movb $9, %cl
  add $16, %rbx
ret
