import random


class Animal:
    """Animal class"""

    def __init__(self, age):
        # specific to each instance
        self.age = age

    def communicate(self):
        pass

    def get_age(self):
        return self.age


class Mammal(Animal):
    def __init__(self, age):
        Animal.__init__(self, age)
        self.pregnant = False

    def set_pregnant_stat(self, p):
        self.pregnant = p

    def is_it_pregnant(self):
        return self.pregnant


class Dog(Mammal):
    def __init__(self, age, breed):
        Mammal.__init__(self, age)
        self.breed = breed

    def communicate(self):
        print "Bark bark bark"

    def set_breed(self, breed):
        self.breed = breed

    def get_breed(self):
        return self.breed

if __name__ == '__main__':
    print "Dog\n---"
    d = Dog(3, "")
    d.communicate()

    print "age: {}".format(d.get_age())

    d.set_breed("Cocker spaniel")

    print "breed: {}".format(d.get_breed())
    print "pregnant: {}".format(d.is_it_pregnant())

