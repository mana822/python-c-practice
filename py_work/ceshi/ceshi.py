class Employee:
    def __init__(self, firstname, lastname, money):
        """姓、名、年薪"""
        self.firstname = firstname
        self.lastname = lastname
        self.money = money
    # __init__里面不能有返回值，默认返回None
    def give_raise(self, append = 5000):
        self.money += append
        return self.money