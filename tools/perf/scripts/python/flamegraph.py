# flamegraph.py - create flame graphs from perf samples
# SPDX-License-Identifier: GPL-2.0
#
# Usage:
#
#     perf record -a -g -F 99 sleep 60
#     perf script report flamegraph
#
# Combined:
#
#     perf script flamegraph -a -F 99 sleep 60
#
# Written by Andreas Gerstmayr <agerstmayr@redhat.com>
# Flame Graphs invented by Brendan Gregg <bgregg@netflix.com>
# Works in tandem with d3-flame-graph by Martin Spier <mspier@netflix.com>
<<<<<<< HEAD
#
# pylint: disable=missing-module-docstring
# pylint: disable=missing-class-docstring
# pylint: disable=missing-function-docstring
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

from __future__ import print_function
import sys
import os
import io
import argparse
import json
<<<<<<< HEAD
import subprocess

# pylint: disable=too-few-public-methods
class Node:
    def __init__(self, name, libtype):
        self.name = name
        # "root" | "kernel" | ""
        # "" indicates user space
=======


class Node:
    def __init__(self, name, libtype=""):
        self.name = name
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
        self.libtype = libtype
        self.value = 0
        self.children = []

<<<<<<< HEAD
    def to_json(self):
=======
    def toJSON(self):
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
        return {
            "n": self.name,
            "l": self.libtype,
            "v": self.value,
            "c": self.children
        }


class FlameGraphCLI:
    def __init__(self, args):
        self.args = args
<<<<<<< HEAD
        self.stack = Node("all", "root")
=======
        self.stack = Node("root")
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

        if self.args.format == "html" and \
                not os.path.isfile(self.args.template):
            print("Flame Graph template {} does not exist. Please install "
                  "the js-d3-flame-graph (RPM) or libjs-d3-flame-graph (deb) "
                  "package, specify an existing flame graph template "
                  "(--template PATH) or another output format "
                  "(--format FORMAT).".format(self.args.template),
                  file=sys.stderr)
            sys.exit(1)

<<<<<<< HEAD
    @staticmethod
    def get_libtype_from_dso(dso):
        """
        when kernel-debuginfo is installed,
        dso points to /usr/lib/debug/lib/modules/*/vmlinux
        """
        if dso and (dso == "[kernel.kallsyms]" or dso.endswith("/vmlinux")):
            return "kernel"

        return ""

    @staticmethod
    def find_or_create_node(node, name, libtype):
        for child in node.children:
            if child.name == name:
=======
    def find_or_create_node(self, node, name, dso):
        libtype = "kernel" if dso == "[kernel.kallsyms]" else ""
        if name is None:
            name = "[unknown]"

        for child in node.children:
            if child.name == name and child.libtype == libtype:
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
                return child

        child = Node(name, libtype)
        node.children.append(child)
        return child

    def process_event(self, event):
<<<<<<< HEAD
        pid = event.get("sample", {}).get("pid", 0)
        # event["dso"] sometimes contains /usr/lib/debug/lib/modules/*/vmlinux
        # for user-space processes; let's use pid for kernel or user-space distinction
        if pid == 0:
            comm = event["comm"]
            libtype = "kernel"
        else:
            comm = "{} ({})".format(event["comm"], pid)
            libtype = ""
        node = self.find_or_create_node(self.stack, comm, libtype)

        if "callchain" in event:
            for entry in reversed(event["callchain"]):
                name = entry.get("sym", {}).get("name", "[unknown]")
                libtype = self.get_libtype_from_dso(entry.get("dso"))
                node = self.find_or_create_node(node, name, libtype)
        else:
            name = event.get("symbol", "[unknown]")
            libtype = self.get_libtype_from_dso(event.get("dso"))
            node = self.find_or_create_node(node, name, libtype)
        node.value += 1

    def get_report_header(self):
        if self.args.input == "-":
            # when this script is invoked with "perf script flamegraph",
            # no perf.data is created and we cannot read the header of it
            return ""

        try:
            output = subprocess.check_output(["perf", "report", "--header-only"])
            return output.decode("utf-8")
        except Exception as err:  # pylint: disable=broad-except
            print("Error reading report header: {}".format(err), file=sys.stderr)
            return ""

    def trace_end(self):
        stacks_json = json.dumps(self.stack, default=lambda x: x.to_json())

        if self.args.format == "html":
            report_header = self.get_report_header()
            options = {
                "colorscheme": self.args.colorscheme,
                "context": report_header
            }
            options_json = json.dumps(options)

            try:
                with io.open(self.args.template, encoding="utf-8") as template:
                    output_str = (
                        template.read()
                        .replace("/** @options_json **/", options_json)
                        .replace("/** @flamegraph_json **/", stacks_json)
                    )
            except IOError as err:
                print("Error reading template file: {}".format(err), file=sys.stderr)
                sys.exit(1)
            output_fn = self.args.output or "flamegraph.html"
        else:
            output_str = stacks_json
=======
        node = self.find_or_create_node(self.stack, event["comm"], None)
        if "callchain" in event:
            for entry in reversed(event['callchain']):
                node = self.find_or_create_node(
                    node, entry.get("sym", {}).get("name"), event.get("dso"))
        else:
            node = self.find_or_create_node(
                node, entry.get("symbol"), event.get("dso"))
        node.value += 1

    def trace_end(self):
        json_str = json.dumps(self.stack, default=lambda x: x.toJSON())

        if self.args.format == "html":
            try:
                with io.open(self.args.template, encoding="utf-8") as f:
                    output_str = f.read().replace("/** @flamegraph_json **/",
                                                  json_str)
            except IOError as e:
                print("Error reading template file: {}".format(e), file=sys.stderr)
                sys.exit(1)
            output_fn = self.args.output or "flamegraph.html"
        else:
            output_str = json_str
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
            output_fn = self.args.output or "stacks.json"

        if output_fn == "-":
            with io.open(sys.stdout.fileno(), "w", encoding="utf-8", closefd=False) as out:
                out.write(output_str)
        else:
            print("dumping data to {}".format(output_fn))
            try:
                with io.open(output_fn, "w", encoding="utf-8") as out:
                    out.write(output_str)
<<<<<<< HEAD
            except IOError as err:
                print("Error writing output file: {}".format(err), file=sys.stderr)
=======
            except IOError as e:
                print("Error writing output file: {}".format(e), file=sys.stderr)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
                sys.exit(1)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Create flame graphs.")
    parser.add_argument("-f", "--format",
                        default="html", choices=["json", "html"],
                        help="output file format")
    parser.add_argument("-o", "--output",
                        help="output file name")
    parser.add_argument("--template",
                        default="/usr/share/d3-flame-graph/d3-flamegraph-base.html",
<<<<<<< HEAD
                        help="path to flame graph HTML template")
    parser.add_argument("--colorscheme",
                        default="blue-green",
                        help="flame graph color scheme",
                        choices=["blue-green", "orange"])
    parser.add_argument("-i", "--input",
                        help=argparse.SUPPRESS)

    cli_args = parser.parse_args()
    cli = FlameGraphCLI(cli_args)
=======
                        help="path to flamegraph HTML template")
    parser.add_argument("-i", "--input",
                        help=argparse.SUPPRESS)

    args = parser.parse_args()
    cli = FlameGraphCLI(args)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

    process_event = cli.process_event
    trace_end = cli.trace_end
