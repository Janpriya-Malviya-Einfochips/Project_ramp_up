import pytest

@pytest.fixture()
def my_fixture():
    print "\nI'm the fixture"

def test_my_fixture_1(my_fixture):
    print "I'm the test1"

#########################################
# Other Ways of Using pytest Fixtures
#########################################
#########################################
# Way -1
#########################################
@pytest.mark.usefixtures('my_fixture')
def test_my_fixture_2():
    print "I'm the test2"



#########################################
# Way -2
#########################################
@pytest.mark.usefixtures('my_fixture')
class Test:
    def test3(self):
        print "I'm the test 3"

    def test4(self):
        print "I'm the test 4"

#########################################
# Way -3 By Using autouse
#########################################
import pytest

@pytest.fixture(autouse=True)
def my_fixture1():
    print "\nI'm the fixture1"

def test_my_fixture5():
    print "I'm the test5"

class Test2:
    def test6(self):
        print "I'm the test 6"

    def test7(self):
        print "I'm the test 7"





