$ cc/debug io.c,set.c,paslib.c 
$ library/create/replace ptoc io.obj,set.obj,paslib.obj
$ write sys$output "Done..." 
