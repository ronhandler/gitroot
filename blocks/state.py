class Block:
    def __init__(self, name):
        self.name = name
    def __str__(self):
        return str(self.name)

class State:

    def __init__(self, state_str_list):
        self.cols = []
        for i,col in enumerate(state_str_list):
            self.cols.append([])
            for j,block in enumerate(col):
                self.cols[i].append(Block(state_str_list[i][j]))
    
    def __str__(self):
        strings = []
        for i in range(0,len(self.cols)):
            strings.append("")
            for j in range(0,len(self.cols[i])):
                strings[i] = strings[i] + str(self.cols[i][j])
        maxlen = len(max(strings, key=len))
        for i in range(0,len(self.cols)):
            if len(strings[i]) < maxlen:
                strings[i] = strings[i] + " " * (maxlen-len(strings[i]))
        s = ""
        for j in range(len(strings[i])-1, -1, -1):
            for i in range(0,len(strings)):
                s = s + strings[i][j] + " "
            s = s + "\n"

        for i in range(0,len(strings)):
            s = s + "= "
        s = s + "\n"

        for i in range(0,len(strings)):
            s = s + str(i) + " "

        return s
