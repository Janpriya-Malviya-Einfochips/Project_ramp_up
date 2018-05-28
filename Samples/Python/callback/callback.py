##Normal Callback
#def myCallback(a,j):
##	print("MyCallbcak Called a=>", a, " j=>", j)
#	
#
#
#def testCallback(cb,one,two):
#	print("Calling my callback functiuon->")
#	cb(one,two)
#
#
#testCallback(myCallback,1,2)
#

#class A:
#  def __init__(self, flag):
#    self.flag = flag
#
#  def func(self):
#    print self.flag
#
#a = A(1)
#b = A(2)
#callback_a = a.func
#callback_b = b.func
#
#print "typeof(callback_a) = {0}".format(type(callback_a))
#print "typeof(callback_b) = {0}".format(type(callback_b))
#
#print "typeof(callback_a.__func__) = {0}".format(type(callback_a.__func__))
#print "typeof(callback_b.__func__) = {0}".format(type(callback_b.__func__))
#
#print "'callback_a.__func__ is callback_b.__func__'  is {0}".format(callback_a.__func__ is callback_b.__func__)
#
#callback_a()
#callback_b()

from __future__ import print_function
import sys
from time import sleep

class FileReporter(object):

    def __init__(self, filename):
        self._filename = filename
        try:
            self._fil = open(self._filename, "w")
        except IOError as ioe:
            sys.stderr.write("While opening {}, caught IOError: {}\n".format(
                self._filename, repr(ioe)))
            sys.exit(1)

    def report(self, message):
        self._fil.write(message)

class ScreenReporter(object):

    def __init__(self, dest):
        self._dest = dest

    def report(self, message):
        self._dest.write(message)

def square(i):
    return i * i

def cube(i):
    return i * i * i

def processor(process, times, report_interval, reporter):
    result = 0
    for i in range(1, times + 1):
        result += process(i)
        sleep(0.1)
        reporter("Items processed: {}. Running result: {}.\n".format(i, result))
        if i % report_interval == 0:
            # This is the call to the callback method 
            # that was passed to this function.
            #reporter.report("Items processed: {}. Running result: {}.\n".format(i, result))
            reporter("Items processed: {}. Running result: {}.\n".format(i, result))

file_reporter = FileReporter("processor_report.txt")
fn1 = file_reporter.report;

processor(square, 20, 5, fn1)

stdout_reporter = ScreenReporter(sys.stdout)
fn2 = stdout_reporter.report;

processor(square, 20, 5, fn2)

stderr_reporter = ScreenReporter(sys.stderr)
fn3 = stderr_reporter.report;
processor(square, 20, 5, fn3)
