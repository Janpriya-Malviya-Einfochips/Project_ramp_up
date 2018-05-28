# Basic pytest script
#what i found in bellowed sample:
#		1. File must be start with test_
#		2. nb of functons start with test_  will be our test case
#		3. we can run using pytest in current directory
#		4. test_raises_exception_on_non_string_arguments will pass only if exectption rasied.
#
import pytest

def capital_case(x):
	if not isinstance(x, str):
		raise TypeError('Please provide a string argument')
	return x.capitalize()
      
def test_capital_case():
    assert capital_case('semaphore') == 'Semaphore'

def test_raises_exception_on_non_string_arguments():
    with pytest.raises(TypeError):
        capital_case(9)
