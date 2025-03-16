from ADTBag import ADTBag
from ADTIterator import ADTIterator

def main():
    bag = ADTBag()

    bag.add(1)
    bag.add(2)
    bag.add(3)
    bag.add(4)
    bag.add(5)

    assert bag.length() == 5
    bag.remove(4)
    assert bag.length() == 4
    assert bag.search(3) is True
    assert bag.search(4) is False
    bag.add(2)
    assert bag.nrOccurence(2) == 2

    ite = ADTIterator(bag)
    assert ite.valid() is True
    ite.next()
    assert ite.valid() is True
    assert ite.getCurrent() == 2


main()
