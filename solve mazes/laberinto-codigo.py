import sys 


class Node(): #clase llama node, estara siguiendo a state, parent y action
    def __init__(self, state, parent, action):
        self.state = state
        self.parent = parent
        self.action = action


class StackFrontier(): #clase llamada StackFrontier para generar un objeto. La idea aqui es que se quiere creear un objeto...
                       #... que guarde todo la informacion del Frontier y al mismo tiempo poder tener objetos para poder manipular
                       #... al objeto inicial.
                       #... depth-first search
    def __init__(self):
        self.frontier = [] #inicialmente mi frontier es representado por una lista vasia para empezar.

    def add(self, node): # add funcion que nos permite agregar cosas a nuestro frontier
        self.frontier.append(node) #append agraga al final de la lista

    def contains_state(self, state): # funcion que se encagar de resivar si el frontier tiene algun estado particular
        return any(node.state == state for node in self.frontier)

    def empty(self): #funcion que revisa si el frontier esta vacio
        return len(self.frontier) == 0

    def remove(self): # funcion para remover elementos del frontier
        if self.empty():
            raise Exception("empty frontier")
        else:
            node = self.frontier[-1]
            self.frontier = self.frontier[:-1]
            return node


class QueueFrontier(StackFrontier): #breadth-first search

    def remove(self):
        if self.empty():
            raise Exception("empty frontier")
        else:
            node = self.frontier[0]
            self.frontier = self.frontier[1:]
            return node

class Maze(): #declarar una clase como maze, para interpretar un blog de texto como un laberinto

    def __init__(self, filename):

        # Se lee el archivo
        with open(filename) as f:
            contents = f.read()

        # Se valida si el laberinto tiene un final o un inicio
        if contents.count("A") != 1:
            raise Exception("El laberinto debe de tener un punto de inicio")
        if contents.count("B") != 1:
            raise Exception("El laberinto debe de tener una meta")

        # Se determina el alto y ancho del laberinto
        contents = contents.splitlines()
        self.height = len(contents)
        self.width = max(len(line) for line in contents)

        # Mantine un seguimiento de las paredes
        self.walls = []
        for i in range(self.height):
            row = []
            for j in range(self.width):
                try:
                    if contents[i][j] == "A":
                        self.start = (i, j)
                        row.append(False)
                    elif contents[i][j] == "B":
                        self.goal = (i, j)
                        row.append(False)
                    elif contents[i][j] == " ":
                        row.append(False)
                    else:
                        row.append(True)
                except IndexError:
                    row.append(False)
            self.walls.append(row)

        self.solution = None


    def print(self):
        solution = self.solution[1] if self.solution is not None else None
        print()
        for i, row in enumerate(self.walls):
            for j, col in enumerate(row):
                if col:
                    print("█", end="")
                elif (i, j) == self.start:
                    print("A", end="")
                elif (i, j) == self.goal:
                    print("B", end="")
                elif solution is not None and (i, j) in solution:
                    print("*", end="")
                else:
                    print(" ", end="")
            print()
        print()


    def neighbors(self, state):
        row, col = state
        candidates = [
            ("up", (row - 1, col)),
            ("down", (row + 1, col)),
            ("left", (row, col - 1)),
            ("right", (row, col + 1))
        ]

        result = []
        for action, (r, c) in candidates:
            if 0 <= r < self.height and 0 <= c < self.width and not self.walls[r][c]:
                result.append((action, (r, c)))
        return result


    def solve(self):
        """Encuentra una solucion al laberinto si no hay una se cierra"""

        # Realizar un listado de las instancias exploradas
        self.num_explored = 0 #se va atener un conteo de cuantas instancias hemos explorado

        # Iniciar frontier desde la posicion inicial
        start = Node(state=self.start, parent=None, action=None) #Este nodo representa el estado inicial
        frontier = StackFrontier() #Se empieza con el frontier declarado al comienzo
        frontier.add(start) #Se empieza a buscar

        # incia un set vacio de exploracion
        self.explored = set()

        # mantiene el ciclo hasta que se encuentre una solucion
        while True:

            # Si no hay nada que mas explorar, entonces no hay camino
            if frontier.empty():
                raise Exception("no hay solucion")

            # Se elige un nodo del frontier, si aun hay solucion se elimina el nodo y se aumenta en +1 el numero de de instancias exploradas
            node = frontier.remove()
            self.num_explored += 1

            # Si el nodo es la solucion entonces se encontro la solucion
            if node.state == self.goal: # Si el estado del nodo es la solucion entonces llegamos a la meta, si es la meta se hace un recuento de lo que se realizo para llegar a este
                actions = []            #el recuento se hacen en base a las celdas y acciones que se analizaron
                cells = []
                while node.parent is not None:
                    actions.append(node.action) #aqui se guardan las acciones realizada
                    cells.append(node.state)    # aqui se guarda el estado del nodo
                    node = node.parent
                actions.reverse()
                cells.reverse()
                self.solution = (actions, cells)
                return

            # Marcar el nodo como explorado
            self.explored.add(node.state)

            # Agregar neighbour al frontier
            for action, state in self.neighbors(node.state):
                if not frontier.contains_state(state) and state not in self.explored:
                    child = Node(state=state, parent=node, action=action)
                    frontier.add(child)


    def output_image(self, filename, show_solution=True, show_explored=False):
        from PIL import Image, ImageDraw
        cell_size = 50
        cell_border = 2

        # Crear una imagen en blanco
        img = Image.new(
            "RGBA",
            (self.width * cell_size, self.height * cell_size),
            "black"
        )
        draw = ImageDraw.Draw(img)

        solution = self.solution[1] if self.solution is not None else None
        for i, row in enumerate(self.walls):
            for j, col in enumerate(row):

                # paredes
                if col:
                    fill = (40, 40, 40)

                # inicio
                elif (i, j) == self.start:
                    fill = (255, 0, 0)

                # meta
                elif (i, j) == self.goal:
                    fill = (0, 171, 28)

                # solucion
                elif solution is not None and show_solution and (i, j) in solution:
                    fill = (220, 235, 113)

                # explorado
                elif solution is not None and show_explored and (i, j) in self.explored:
                    fill = (212, 97, 85)

                # celdas vacias
                else:
                    fill = (237, 240, 252)

                # dibujar celdas
                draw.rectangle(
                    ([(j * cell_size + cell_border, i * cell_size + cell_border),
                      ((j + 1) * cell_size - cell_border, (i + 1) * cell_size - cell_border)]),
                    fill=fill
                )

        img.save(filename)


if len(sys.argv) != 2:
    sys.exit("Usage: python maze.py maze.txt")

m = Maze(sys.argv[1])
print("laberinto:")
m.print()
print("Resolviendo...")
m.solve()
print("Instancias exploradas:", m.num_explored)
print("Solucion:")
m.print()
m.output_image("laberinto.png", show_explored=True)