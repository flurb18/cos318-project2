# entry.S
# COS 318, Fall 2019: Project 2 Non-Preemptive Kernel
# Entry points into the kernel for processes and threads

.data

.text
.code32

.globl  kernel_entry
kernel_entry:
	pushl	%ebp
	movl	%esp, %ebp
	
	movl	8(%esp), %eax
	cmp	$0, %eax
	jne	dont_yield
	call	do_yield
	jmp	done
dont_yield:	
	cmp	$1, %eax
	jne	dont_exit
	call	do_exit
	jmp	done
dont_exit:
	jmp	done
done:
	leave
	ret

.globl  scheduler_entry
scheduler_entry:
	// Push scratch register and eflags
	pushl	%eax
	pushfl
	// Get address of currently running pcb
	movl	current_running, %eax
	// Push the rest of the registers except stack pointer
	pushl	%ecx
	pushl	%edx
	pushl	%ebx
	pushl	%esi
	pushl	%edi
	pushl	%ebp
	// Save stack pointer in PCB of current_running
	movl	%esp, (%eax)

	// Update current_running
	call	scheduler
	/* scheduler updates the new current_running's start time to
	   get_timer() */
/*---------------------------------------------------------------------------*/
	/* This section of code is the number of instructions we need to
	   add to the start time */
	# Get address of new pcb
	movl	current_running, %eax
	# Set the stack pointer
	movl	(%eax), %esp
	# Pop the registers off the stack
	popl	%ebp
	popl	%edi
	popl	%esi
	popl	%ebx
	popl	%edx
	popl	%ecx
	popfl
	pop	%eax
/*---------------------------------------------------------------------------*/
	ret
