#!/bin/bash

ps -ef | grep 'soal3' | grep -v grep | awk '{print $2}' | xargs -r kill -9