lock_acquire:
    li $t1, 1       # Load 1 into $t1 (to indicate the lock is taken)
    move $t2, $t1   # Move the lock value (1) to $t2
    li $t3, 0       # Load 0 into $t3 (to store the thread ID)
    move $t3, $a1   # Move the thread ID (from $a1) to $t3
    sll $t3, $t3, 8 # Shift the thread ID left by 8 bits
    or $t2, $t2, $t3 # Combine the lock value (1) and the thread ID
cas_acquire:
    ll $t0, ($a0)   # Load linked (atomically read the lock value)
    beq $t0, $zero, cas_acquire_success # Branch if the lock is available
    
    # Lock is already taken, try to acquire it
    move $t4, $t2   # Move the combined lock value and thread ID to $t4
    sc $t4, ($a0)   # Store conditional (atomically write the lock value)
    beqz $t4, cas_acquire # Branch if the store failed (lock not acquired)
    
    # Lock acquired
cas_acquire_success:
    # Critical section code goes here
    
    # Release the lock
    li $t3, 0       # Load 0 into $t3 (to clear the thread ID)
    sw $t3, ($a0)   # Store 0 to release the lock
    jr $ra         # Return from the lock_acquire function

lock_release:
    li $t3, 0       # Load 0 into $t3 (to clear the thread ID)
    sw $t3, ($a0)   # Store 0 to release the lock
    jr $ra         # Return from the lock_release function