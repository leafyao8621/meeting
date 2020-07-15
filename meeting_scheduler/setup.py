from setuptools import setup, Extension

meetingscheduler = Extension("meetingscheduler",
                             sources=["src/tools/connector.c",
                                      "src/tools/resetter.c",
                                      "src/tools/scheduler.c",
                                      "src/util/generator.c",
                                      "src/util/mt19937.c",
                                      "src/extension.c"],
                             include_dirs=["/usr/include/mysql",
                                           "/usr/include/mysql/mysql"],
                             library_dirs=["/usr/lib"],
                             libraries=["mariadb"])
setup(name='meetingscheduler', version='1.0',  \
      ext_modules=[meetingscheduler])
