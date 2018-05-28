import pytest
#########################################
# Returning Value form Fixure -> fixer dose not required to print thing it required to return object
#########################################
@pytest.fixture()
def my_fixture():
    data = {'x': 1, 'y': 2, 'z': 3}
    return data

@pytest.mark.usefixtures('my_fixture')
def test_my_fixture(my_fixture):
    assert my_fixture['x'] == 1					# """"my_fixture""""['x'] is same name as  test_my_fixture(""""my_fixture""""):


#########################################
# Add fixer with teardown
#		1. If you want to run something after a test with a fixture has completed, we can use finalizers
#		2. To do this, we get access to the request fixture from pytest. A finalizer is a function inside a fixture that will run after every test that a fixture is included.
#       3. Take care about space and tab
#########################################
@pytest.fixture()
def my_tear_down_fixture(request):
    data = {'x': 1, 'y': 2, 'z': 3}

    def fin():
        print "\nmy_tear_down_fixture callled"

    request.addfinalizer(fin)
    print "\nmy_tear_up_fixture callled"
    return data

@pytest.mark.usefixtures('my_tear_down_fixture')
def test_my_fixture2(my_tear_down_fixture):
    print "\ntest_my_fixture2 "
    assert my_tear_down_fixture['x'] == 1					# """"my_fixture""""['x'] is same name as  test_my_fixture(""""my_fixture""""):
