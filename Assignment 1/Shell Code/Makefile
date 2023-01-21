default:first
	gcc -pthread basic_shell.c
	./a.out


first:
	gcc cat_file.c -o cat_exec
	gcc mkdir_file.c -o mkdir_exec
	gcc ls_file.c -o ls_exec
	gcc rm_file.c -o rm_exec
	gcc date_file.c -o date_exec
	gcc empty_file.c -o empty_exec

clean:
	rm cat_exec mkdir_exec ls_exec rm_exec date_exec a.out empty_exec
