# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'eecs'
copyright = '2025, Dimitri'
author = 'Dimitri'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

import sys
from pathlib import Path

sys.path.append(str(Path('./.venv/lib/python3.13/site-packages').resolve()))

extensions = ['breathe', 'myst_parser', 'sphinx.ext.graphviz']

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'shibuya'
html_theme_options = {
    'accent_color': 'grass',
}
html_static_path = []

# -- Breathe configuration ---------------------------------------------------
breathe_default_project = 'eecs'

import subprocess, os

def configure_doxyfile(input_dir: str, output_dir: str) -> None:
    with open('Doxyfile.in', 'r') as file:
        content = file.read()

    content = content.replace('@DOXYGEN_INPUT_DIR@', input_dir)
    content = content.replace('@DOXYGEN_OUTPUT_DIR@', output_dir)

    with open('Doxyfile', 'w') as file:
        file.write(content)

read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'

breathe_projects = {}

if read_the_docs_build:
    input_dir = '../src'
    output_dir = 'build'
    configure_doxyfile(input_dir, output_dir)
    subprocess.call('doxygen', shell=True)
    breathe_projects['eecs'] = output_dir + '/xml'
