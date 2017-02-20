import random


class Person:
    """Person class"""

    # shared by all instances
    species = "human"

    def __init__(self, age):
        # specific to each instance
        self.age = age
        # underscores are the convention for private variables
        self.__id = random.randint(0, 10000)

    def about_me(self):
        print "I am a person, {} years old".format(self.age)

    def get_age(self):
        return self.age

    def get_id(self):
        return self.__id


class Student(Person):
    def __init__(self, age, course):
        Person.__init__(self, age)
        self.course = course

    def about_me(self):
        print "I am a student in grade {} with age {}".format(self.course,
                                                              self.get_age())

    def set_course(self, c):
        self.course = c


if __name__ == '__main__':
    p = Person(33)
    p.about_me()
    print "id: {}".format(p.get_id())

    s = Student(33, 11)
    s.set_course(10)
    s.about_me()
    # old style print format
    print "id: %d" % s.get_id()

