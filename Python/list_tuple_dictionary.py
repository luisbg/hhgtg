import random

if __name__ == '__main__':
    tuple = (1, 2, 3)
    list = []
    dict = {}

    # tupples are immutable
    print "tuple:"
    print "first element is: " + str(tuple[0])
    print "entire tuple: " + str(tuple)

    print ""

    # you can append, instert, remove and more from a list
    print "list: "
    list.append(4)
    list.append(6)
    list.insert(1, 5)
    list.append(7)
    list.append(5)
    print "first element is: " + str(list[0])
    print "entire list is: " + str(list)
    print "5 is listed this many times: " + str(list.count(5))
    print "and located at position: " + str(list.index(5))
    print "length of list is: " + str(len(list))

    print ""

    # sets work with key-value pairs
    dict['a'] = 8
    dict['b'] = 9
    dict['d'] = 11
    dict['c'] = 10
    print "the value matching the key 'a' is" + str(dict['a'])
    del dict['d']
    print "the keys are" + str(dict.keys())
    print "entire dict is: " + str(dict)
    print "one by one: "
    for k, v in dict.items():
         print(k, v)
    if 'a' in dict:
        print "a is in the dictionary"
