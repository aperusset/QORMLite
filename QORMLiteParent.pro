TEMPLATE = subdirs

SUBDIRS += \
  code/QORMLite.pro \
  test/QORMLiteTest.pro

test/QORMLiteTest.pro.depends = code/QORMLite.pro
