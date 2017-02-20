import random


class Employee:
    pass


def review(employee):
    if employee.last_review < 2017:
        plan = "is due a review"
    else:
        plan = "isn't due a review"

    print "{}, from {}, {}".format(employee.name, employee.dept, plan)

if __name__ == '__main__':
    john = Employee()  # Create an empty employee record

    # Fill the fields of the record
    john.name = 'John Doe'
    john.dept = 'computer lab'
    john.salary = 1000
    john.last_review = 2016

    review(john)

