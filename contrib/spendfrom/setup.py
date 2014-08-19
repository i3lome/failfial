from distutils.core import setup
setup(name='btcspendfrom',
      version='1.0',
      description='Command-line utility for vikingcoin "coin control"',
      author='Gavin Andresen',
      author_email='gavin@vikingcoinfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
