import pytest

class InsufficientAmount(Exception):
    pass


class Wallet(object):

    def __init__(self, initial_amount=0):
        self.balance = initial_amount

    def spend_cash(self, amount):
        if self.balance < amount:
            raise InsufficientAmount('Not enough available to spend {}'.format(amount))
        self.balance -= amount

    def add_cash(self, amount):
        self.balance += amount
        

##########################################
#what i found in bellowed sample:
##########################################
#		1. Each time it is required to create object of wallet().
#		   due to this python.testfixer came in picture 
##########################################

#def test_default_initial_amount():
#    wallet = Wallet()
#    assert wallet.balance == 0
#
#def test_setting_initial_amount():
#    wallet = Wallet(100)
#    assert wallet.balance == 100#
#
#def test_wallet_add_cash():
#    wallet = Wallet(10)
#    wallet.add_cash(90)
#    assert wallet.balance == 100
#
#def test_wallet_spend_cash():
#    wallet = Wallet(20)
#    wallet.spend_cash(10)
#    assert wallet.balance == 10
#def test_wallet_spend_cash_raises_exception_on_insufficient_amount():
#    wallet = Wallet()
#    with pytest.raises(InsufficientAmount):
#       wallet.spend_cash(100)

##########################################
#Above sample with test fixer:
##########################################
#		1. Fixture must retun an object 
#		2. Each test is provided with a newly-initialized Wallet instance, and not one that has been used in another test.
#		3.
##########################################
@pytest.fixture
def empty_wallet():
    '''Returns a Wallet instance with a zero balance'''
    return Wallet()

@pytest.fixture
def wallet():
    '''Returns a Wallet instance with a balance of 20'''
    return Wallet(20)

def test_default_initial_amount(empty_wallet):
    assert empty_wallet.balance == 0

def test_setting_initial_amount(wallet):
    assert wallet.balance == 20

def test_wallet_add_cash(wallet):
    wallet.add_cash(80)
    assert wallet.balance == 100

def test_wallet_spend_cash(wallet):
    wallet.spend_cash(10)
    assert wallet.balance == 10

def test_wallet_spend_cash_raises_exception_on_insufficient_amount(empty_wallet):
    with pytest.raises(InsufficientAmount):
        empty_wallet.spend_cash(100)
