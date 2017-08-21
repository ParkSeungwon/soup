all : 
	make -C src/
	make -C gtk/
	make -C obj/

PHONY : clean

clean :
	rm obj/*.o obj/*.x *.x

ls :
	echo $(EXE)
