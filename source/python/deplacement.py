#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from pipes import PipesModule

            
if __name__ == "__main__":
    with PipesModule("deplacement") as pipes:
        pipes.record()
        while True:
            obj = pipes.readMessage()
            if obj:
                print(obj)
        