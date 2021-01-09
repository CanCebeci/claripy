'''@file
@brief This file is used to autogenerate op subclasses
This file *will* overwrite existing files

Within the defined io directory there must exist a config json file.
The config file will contain a list of dicts, each containing three things:
{
    'file' : <file_path>,
    'op' : <op name>,
    'args' : <a list of unnamed argument types>
}
These entries will be used to autogenerate, in the autogen_dir,
a set of files that contain the necessary subclasses of op,
along with shared pointer aliases to each as needed.

Finally generates autogen.hpp in io_dir
'''

import argparse
import json
import sys
import os


# Constants
io_dir = os.path.realpath('op')
autogen_dir_name = 'autogen'
namespace = 'Expresson::Raw'
autogen_dir = os.path.join(io_dir, autogen_dir_name)
config_f = os.path.join(io_dir, 'autogen.json')
autogenhpp = os.path.join(io_dir, 'autogen.hpp')
header_guard_prefix = '__EXPRESSION_RAW_'


# Helper functions


def header_guard_top(fname):
    fname = fname.split('.')[0]
    return header_guard_prefix + fname.upper() + '_HPP__'

def header_guard_autogen(fname):
    fname = fname.split('.')[0]
    return header_guard_prefix + autogen_dir_name.upper() + '_' + fname.upper() + '_HPP__'

def create_header_guard(header_guard):
    return '#ifndef ' + header_guard + '\n#define ' + header_guard + '\n'


# Generation functions


def generate_header(file, op, args):
    doxygen = '/**\n * @file\n * @brief This file defines relevant subclasses of ' + op
    doxygen += '\nThis file was autogenerated by autogen.py'
    prefix = doxygen + '\n\n' + create_header_guard(header_guard_autogen(file)) + '\n'
    suffix = '\n\n#endif'
    # TODO: also have to handle op namespace etc

def generate_source(file, op, args):
    prefix = '/** @file */\n#include "' + file '"\n\n'
    # TODO:

def generate_autogen(files):
    doxygen = '/**\n * @file\n * @brief This file includes all headers used by autogen.py'
    doxygen += '\nThis file was autogenerated by autogen.py'
    prefix = doxygen + '\n\n' + create_header_guard(header_guard_top(autogenhpp)) + '\n'
    mid = '\n'.join([ '#include "' + i + '"' for i in files ])
    suffix = '\n\n#endif'
    output = prefix + mid + suffix
    with open(autogenhpp, 'w') as f:
        f.write(output)


# Other functions


def verify_config(config):
    assert(type(config) == list, 'Config must have a list type')
    # Entry verification
    for entry in config:
        assert(type(entry) == dict, 'Config entry of improper type')
        assert(set(entry.keys()) == ['file', 'op', 'args'], 'Config entry has improper keys')
        # File verification
        assert(type(config['file']) == str, 'Config entry["file"] should be of type str')
        assert(os.path.exists(os.path.exists(os.path.join(input_dir, config['file'])),
            'Config entry["file"] does not exist');
        # Op verification
        assert(type(config['op']) == str, 'Config entry["op"] should be of type str')
        # Args verification
        assert(type(config['args']) == list, 'Config entry["file"] should be of type list')
        for i in config['args']:
            assert(type(i) == str, 'Config entry["file"] entry should be of type str')

def main():
    # Error checking
    assert(os.path.exists(input_dir), 'Bad input_dir')
    assert(os.path.exists(output_dir), 'Bad output_dir')
    assert(os.path.exists(config_f), 'Missing config file')
    # Verify config file
    with open(config_f) as f:
        config = f.read()
    config = json.loads(config)
    verify_config(config)
    # Generate each file
    files = []
    for entry in config:
        files.append(entry['file'])
        generate_header(**entry)
        generate_source(**entry)
    # Generate op.hpp
    generate_autogen(files)


# Don't run on import
if __name__ == '__main__':
    main()