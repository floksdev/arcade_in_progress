.PHONY: all clean move_game

all:
	@$(MAKE) -C src/core
	@$(MAKE) -C src/graphical_lib/ncurse
	@$(MAKE) -C src/graphical_lib/sfml

clean:
	@$(MAKE) -C src/core clean
	@$(MAKE) -C src/graphical_lib/ncurse clean
	@$(MAKE) -C src/graphical_lib/sfml clean

core: 
	@$(MAKE) -C src/core

games:
	@$(MAKE) -C src/core

graphicals:
	@$(MAKE) -C src/graphical_lib/ncurse
	@$(MAKE) -C src/graphical_lib/sfml

move_lib:
	@mv src/graphical_lib/ncurse/ncurse.so .
	@mv src/graphical_lib/sfml/sfml.so .

fclean: clean
	@rm -f arcade
	@rm -f src/graphical_lib/ncurses.so
	@rm -f src/graphical_lib/sfml.so

re: fclean all


