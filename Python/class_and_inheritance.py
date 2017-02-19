import random

class Person:
    """Person class"""

    # shared by all instances
    species = "human"

    def __init__(self, age):
        # specific to each instance
        self.age = age
        self.id = random.randint(0, 10000)

    def about_me(self):
        print "I am a person," + str(self.age) + " years old."

    def get_age(self):
        return self.age

    def get_id(self):
        return self.id

if __name__ == '__main__':
    p = Person(33)
    p.about_me()
    print "id: " + str(p.get_id())
