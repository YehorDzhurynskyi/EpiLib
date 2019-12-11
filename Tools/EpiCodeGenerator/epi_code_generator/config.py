# TODO: add following params
# output_dir

from sys import argv


class Config:

    def __init__(self):
        self.source_dir = '.'

    def parse_cmd(self):

        if len(argv) < 2:
            return

        self.source_dir = argv[-1]
