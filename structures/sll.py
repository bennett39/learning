class Node(object):
    """
    Creates a node with data and pointer to next node
    (singly linked), initializes to None, None.
    """

    def __init__(self, data=None, next_node=None):
        self.data = data
        self.next_node = next_node

    def get_data(self):
        return self.data

    def get_next(self):
        return self.next_node

    def set_next(self, new_next):
        self.next_node = new_next


class LinkedList(object):
    """
    Creates a singly linked list, initialized to None.
    Usage: list = LinkedList():
    """

    def __init__(self, head=None):
        self.head = head

    def delete(self, data):
        """Search for data, delete if found"""
        current = self.head
        prev = None
        found = False
        while current and found == False:
            if current.get_data() == data:
                found = True
            else:
                prev = current
                current = current.get_next()
        if current is None:
            raise ValueError("Data not in list")
        if found == True:
            if prev is None:
                self.head = current.get_next()
            else:
                prev.set_next(current.get_next())

    def insert(self, data):
        """Add new node"""
        new_node = Node(data)
        new_node.set_next(self.head)
        self.head = new_node

    def printlist(self):
        """Print entire linked list to console"""
        print("---------")
        current = self.head
        while current is not None:
            print(current.get_data())
            current = current.get_next()
        print("---------")


    def reverse(self):
        """Reverse the list iteratively"""
        prev_node = None
        current = self.head
        next_node = None
        while current:
            next_node = current.get_next()
            current.set_next(prev_node)
            prev_node = current
            current = next_node
        self.head = prev_node


    def reverse_util(self, current, prev):
        """Recursive utility for reverse_r function, below"""
        if current.get_next() is None:
            self.head = current
            current.set_next(prev)
            return
        rest = current.get_next()
        current.set_next(prev)
        self.reverse_util(rest, current)


    def reverse_r(self):
        """Reverse list recursively."""
        if self.head is None:
            return
        self.reverse_util(self.head, None)


    def search(self, data):
        """Search for a piece of data"""
        current = self.head
        found = False
        while current and found == False:
            if current.get_data() == data:
                found = True
            else:
                current = current.get_next()
        if current is None:
            raise ValueError("Data not in list")
        return current


    def size(self):
        """Count how many nodes are in the list"""
        current = self.head
        count = 0
        while current:
            count += 1
            current = current.get_next()
        return count


# Tests

# Initialize and insert
sll = LinkedList()
sll.insert("Alex")
sll.insert("Bob")
sll.printlist()

# Size and search
print(sll.size())
print(sll.search("Alex").get_data())

# Insert and delete
sll.insert("Charlie")
sll.printlist()
sll.delete("Bob")
sll.printlist()
sll.insert("David")
sll.insert("Edgar")

# Reverse
sll.printlist()
sll.reverse()
sll.printlist()
sll.reverse_r()
sll.printlist()