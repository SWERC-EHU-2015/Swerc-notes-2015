from queue import deque


class Node:
    def __init__(self, val, parent=None, goto=None):
        self.val = val
        self.children = dict()
        self.fail_goto = goto
        self.parent = parent
        self.pattern_ids = set()


class AhoCorasick:
    def __init__(self):
        self.needle_root = Node(None)
        self.needle_root.fail_goto = self.needle_root
        self.n_needles = 0

    def set_fails(self):
        to_process = deque()
        for child in self.needle_root.children.values():
            child.fail_goto = self.needle_root
            for cchild in child.children.values():
                to_process.append(cchild)

        while len(to_process) > 0:
            node = to_process.popleft()

            # check children of the goto of the parent
            parent_fail_child = node.parent.fail_goto.children.get(node.val, -1)
            if not parent_fail_child == -1:
                node.fail_goto = parent_fail_child
            else:
                root_child = self.needle_root.fail_goto.children.get(node.val,
                                                                     -1)
                if not root_child == -1:
                    node.fail_goto = root_child
                else:
                    node.fail_goto = self.needle_root
            for child in node.children.values():
                to_process.append(child)

    def add_needle(self, needle):
        self.n_needles += 1
        cur_node = self.needle_root
        for char in needle:
            for child in cur_node.children.values():
                if child.val == char:
                    cur_node = child
                    break
            else:
                new = Node(char, parent=cur_node)
                cur_node.children[char] = new
                cur_node = new
        cur_node.pattern_ids.add((self.n_needles, needle))

    def search_in(self, string):
        cur_node = self.needle_root
        found_needles = set()
        for char in string:
            found_needles |= cur_node.pattern_ids

            jump = cur_node.children.get(char, -1)
            if not jump == -1:
                cur_node = jump
            else:
                cur_node = cur_node.fail_goto
        return found_needles
