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
    "accent_color": "grass",
}
html_static_path = ['_static']

# -- Breathe configuration ---------------------------------------------------
breathe_default_project = 'eecs'

import subprocess, os

read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'

if read_the_docs_build:
     subprocess.call('cd ../doxygen; doxygen', shell=True)
