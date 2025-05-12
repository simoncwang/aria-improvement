# Creating Baselines and Testing Adaptive Batching

This folder contains all of the exploration I have done in working on the Aria codeabase. The `exploration.ipynb` Jupyter Notebook contains unstructured
general exploration of testing various combinations of paramaters to recreate experiments or establish baselines.

Most of the important finalized baselines and functions are in `explorationV2.ipynb`. This contains the baselines I settled on, as well as several
functions to plot and compare different batching strategies (like time thresholds).

## Setup

if using Google Colab, just download the results folder and upload it to your Colab, using the `.ipynb` file as the main Colab file.

If using VSCode like me, I would create a Conda environment first

    conda create -n "aria-improvement" python=3.12
    conda activate aria-improvement

then install the required packages

    pip install  -r requirements.txt

Be sure you have the Jupyter extension in VSCode, and make sure the interpreter/kernel is set to your Conda Python environment.
