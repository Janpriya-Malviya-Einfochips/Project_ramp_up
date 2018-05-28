import pytest

#######################################
## Learning about test fixture scope
#       1. function     : Run once per test
#       2. class        : Run once per class of tests
#       3. module       : Run once per module
#       4. session      : Run once per session
########################################
class InsufficientAmount(Exception):
    pass

class Wallet(object):

    def __init__(self, initial_amount=0,test_scope=""):
        self.balance = initial_amount
        self.test_scope = test_scope

    def spend_cash(self, amount):
        if self.balance < amount:
            raise InsufficientAmount('Not enough available to spend {}'.format(amount))
        self.balance -= amount

    def add_cash(self, amount):
        self.balance += amount

#######################################
# Scope : Function
#######################################
#@pytest.fixture(scope="function")
#def scope_fn_empty_wallet(request):
#    '''Returns a Wallet instance with a zero balance'''
#    object = Wallet(0,"Function Test Scope");
#
#    def teardown():
#        print("\nTearDown :  " , object.test_scope)
#
#    request.addfinalizer(teardown);
#    return object
#
#def test_default_initial_amount_WITH_FN_SCOPE(scope_fn_empty_wallet):
#    print("\nTest  :  test_default_initial_amount_WITH_FN_SCOPE started")
#    assert scope_fn_empty_wallet.balance == 0
#    print("\nTest  :  test_default_initial_amount_WITH_FN_SCOPE End")#
#
#
#def test_add_amount_WITH_FN_SCOPE(scope_fn_empty_wallet):
#    print("\nTest  :  test_add_amount_WITH_FN_SCOPE started")
#    assert scope_fn_empty_wallet.balance == 0
#    scope_fn_empty_wallet.add_cash(50)
#    assert scope_fn_empty_wallet.balance == 50
#    print("\nTest  :  test_add_amount_WITH_FN_SCOPE End")

#######################################
# Scope : class
# Test will fail because only one referace will create for scope_class_empty_wallet and it will distroyed after class exited
#######################################
@pytest.fixture(scope="class")
def scope_class_empty_wallet(request):
    object = Wallet(0,"Class Test Scope")

    def teardown():
        print("\nTearDown :  " , object.test_scope)

    print("\nTearUP :  ", object.test_scope)
    request.addfinalizer(teardown)
    return object


@pytest.mark.usefixtures('scope_class_empty_wallet')
class Test_ClassScope:
    def test_default_initial_amount_with_class_scope(self,scope_class_empty_wallet):
        print("\nTest  :  test_default_initial_amount_with_class_scope started")
        assert scope_class_empty_wallet.balance == 0
        scope_class_empty_wallet.add_cash(10)
        print("\nTest  :  test_default_initial_amount_with_class_scope End")

    def test_add_amount_with_class_scope(self,scope_class_empty_wallet):
        print("\nTest  :  test_add_amount_with_class_scope started")
        assert scope_class_empty_wallet.balance == 0
        scope_class_empty_wallet.add_cash(50)
        assert scope_class_empty_wallet.balance == 50
        print("\nTest  :  test_add_amount_with_class_scope End")
