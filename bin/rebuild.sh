#!/usr/bin/env bash

set -e -o pipefail

bindir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd "$bindir"/../

rm -rf .pio/*
pio init --ide clion --board nodemcuv2
pio run
