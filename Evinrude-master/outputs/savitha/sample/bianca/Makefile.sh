CC=gcc
CFLAGS=-O3 -Wall -Wextra -fPIC
ELTS_OBJ=state.o net.o game.o global_state.o

default:bianca

all: bianca test capsule

bianca: $(ELTS_OBJ)
test: state_test game_test profile
caps: capsule.so
pcaps: pseudo_capsule.so
scaps: spin_capsule.so
pscaps: pseudo_spin_capsule.so

state.o: state.c state.h headers.h
        $(CC) -c $< -o $@ $(CFLAGS)
       
net.o: generated/net.c state.h generated/net.h generated/event.h headers.h
        $(CC) -c $< -o $@ $(CFLAGS)

game.o: game.c game.h generated/event.h generated/net.h headers.h
        $(CC) -c $< -o $@ $(CFLAGS)
       
global_state.o: global_state.c global_state.h state.h headers.h
        $(CC) -c $< -o $@ $(CFLAGS)

####### CAPSULE #######
capsule.o: capsule/capsule.c headers.h state.h game.h global_state.h generated/net.h
        $(CC) $(CFLAGS) -fPIC -c $< -o capsule.o

capsule.so: capsule.o $(ELTS_OBJ)
        $(CC) -shared $^ -o $@ -ldl -pthread

####### PSEUDO CAPSULE #######
pseudo_capsule.o: capsule/pseudo_capsule.c headers.h state.h game.h global_state.h generated/net.h
        $(CC) $(CFLAGS) -c $< -o pseudo_capsule.o

pseudo_capsule.so: pseudo_capsule.o $(ELTS_OBJ)
        $(CC) -shared $^ -o $@ -ldl -pthread

####### SPIN CAPSULE #######
spin_capsule.o: capsule/spin_capsule.c headers.h state.h game.h global_state.h generated/net.h
        $(CC) $(CFLAGS) -c $< -o spin_capsule.o

spin_capsule.so: spin_capsule.o $(ELTS_OBJ)
        $(CC) -shared $^ -o $@ -ldl -pthread

####### SPIN CAPSULE #######
pseudo_spin_capsule.o: capsule/pseudo_spin_capsule.c headers.h state.h game.h global_state.h generated/net.h
        $(CC) $(CFLAGS) -c $< -o pseudo_spin_capsule.o

pseudo_spin_capsule.so: pseudo_spin_capsule.o $(ELTS_OBJ)
        $(CC) -shared $^ -o $@ -ldl -pthread

###### TESTS #######
state_test: test/state_test.c state.o net.o global_state.o
        $(CC) $^ -o $@ $(CFLAGS)

game_test: test/game_test.c game.o state.o net.o global_state.o
        $(CC) $^ -o $@ $(CFLAGS)

profile: test/profile.c game.o state.o net.o global_state.o
        $(CC) $^ -o $@ $(CFLAGS)

clean:
        rm -f *.so *.o test/*.o state_test game_test profile
