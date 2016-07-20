#!/usr/bin/env bash

cd static
gulp build

cp -R site/assets ../dynamic_example/themes/dynamic_example_theme/