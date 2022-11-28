CCPP = g++
CPPFLAGS  = -std=c++17
CPPFLAGS += -Iinclude -Ilib
CPPFLAGS += -lpthread # for websocketpp


FILES := $(wildcard src/*.cpp src/*.h src/*/*.cpp src/*/*.h)

all: $(FILES)
	yarn --cwd ./src/gui/frontend run build
	$(CCPP) $^ $(CPPFLAGS) -O2 -o main 
 
debug: $(FILES)
	yarn --cwd ./src/gui/frontend run build
	$(CCPP) $^ $(CPPFLAGS) -O0 -g -o debug

start:
# https://stackoverflow.com/a/5752901
	tmux new-session -d "./main"
	tmux split-window -h "cd ./src/gui/frontend/dist && python -m http.server 8000"
	python -m webbrowser "http://localhost:8000/"
	tmux new-window "pure pursuit gui"
	tmux -2 attach-session -d

# TODO
