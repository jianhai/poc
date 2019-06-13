#!/usr/bin/env python

def reverse(list, number=-1):
    length = len(list)
    ret = []

    if number > length :
        number = length

    if number == -1:
       for i in range(length):
           ret.append(list[length-i-1])
    elif number < 2:
       for i in range(length):
           ret.append(list[i])
    else:
       for i in range(number):
           ret.append(list[number-i-1])
       for i in range(length-number):
           ret.append(list[number+i])

    return ret

def main():
    list = ["0", "1", "2", "3", "5", "6", "7", "8", "9"]
    ret = reverse(list)
    print(ret)

    ret = reverse(list,1)
    print(ret)

    ret = reverse(list, 5)
    print(ret)

    ret = reverse(list, 11)
    print(ret)

if __name__ == "__main__":
    main()
