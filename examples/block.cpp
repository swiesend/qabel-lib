/**
 * @file        block_main.cpp
 * @brief       
 * @author      Michael Ott <michael@king-coder.de>
 *
 * copyright:   (C) 2013 by Michael Ott
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation; either version 3 of 
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

#include <string>
using namespace std;

#include "qbl-block.h"
#include "qbl-block-upload.h"
#include "qbl-block-download.h"

#define VERBOSE false
#define DRY_RUN false
#define SERVER "http://127.0.0.1:7000/"

void usage(char *appName);
void help();

int main(int argc, char **argv)
{
    bool verbose, dryRun;
    std::string input, output, server, address, key, operation, dir;
    int counter = 0;
    QblBlock *block;


    if (argc == 1) {
        usage(argv[0]);

        exit(EXIT_FAILURE);
    }

    while (1) {
        int index = 0;
        char c;
        static struct option options[] = {
            {"help", no_argument, 0, 'h'},
            {"verbose", no_argument, 0, 'v'},
            {"dry-run", no_argument, 0, 'n'},
            {"input", required_argument, 0, 'i'},
            {"output", required_argument, 0, 'o'},
            {"server", required_argument, 0, 's'},
            {"address", required_argument, 0, 'a'},
            {"key", required_argument, 0, 'k'},
            {0, 0, 0, 0},
        };
        c = getopt_long(argc, argv, "hvni:o:s:a:k:", options, &index);
        if (c == -1) {
            break;
        }

        switch (c) {
        case 'h':
            usage(argv[0]);
            help();
            return (EXIT_SUCCESS);
            break;
        case 'v':
            verbose = true;
            break;
        case 'n':
            dryRun = true;
            break;
        case 'i':
            input = optarg;
            break;
        case 'o':
            output = optarg;
            break;
        case 's':
            server = optarg;
            break;
        case 'a':
            address = optarg;
            break;
        case 'k':
            key = optarg;
            break;
        case 'w':
            break;
        //default:
        }
    }

    if (optind < argc) {
        while (optind < argc) {
            switch (counter) {
            case 0:
                operation = argv[optind++];
                counter++;
                break;
            case 1:
                dir = argv[optind++];
                counter++;
                break;
            default:
                fprintf(stderr, "Too much arguments\n\n");
                usage(argv[0]);
                return (EXIT_FAILURE);
                break;
            }
        }
    }

    if (address.length() == 0) {
        fprintf(stderr, "No address or file given\n\n");
        usage(argv[0]);
        return (EXIT_FAILURE);
    } else if (key.length() == 0) {
        fprintf(stderr, "No address or file given\n\n");
        usage(argv[0]);
        return (EXIT_FAILURE);
    }

    printf("%s: %s\n", operation.data(), dir.data());
    block = new QblBlock();

    if (! operation.compare("check")) {
    } else if (! operation.compare("list")) {
        QblBlockBlob blob;
        QblBlockTreeList tree;

        ((QblBlockDownload *)block)->list();
        blob = block->getRootDir();
        tree = QblBlock::getFilesFromDir(blob);

    } else if (! operation.compare("unpack")) {
        QblBlockBlob blob;
        QblBlockTreeList tree;
        QblBlockTreeList::iterator iterator;

        ((QblBlockDownload *)block)->unpack();
        blob = block->getRootDir();
        tree = QblBlock::getFilesFromDir(blob);

        for (iterator = tree.begin(); iterator != tree.end(); iterator++) {
            if (iterator->type == TYPE_FILE) {
                std::vector<char> content;
                content = block->getFileContent(iterator->hash);
                printf("%s\n", std::string(content.begin(), content.end()).data());

                break;
            }
        }
    } else if (! operation.compare("pack")) {
        std::string key = "asdfasdfasdfasdf";
        std::string url = "";
        ((QblBlockUpload *)block)->pack(dir, key, url, output);
    } else if (! operation.compare("update")) {
    } else {
        fprintf(stderr, "Unknown operation \"%s\"\n", operation.data());
        usage(argv[0]);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

void usage(char *appName)
{
    fprintf(stdout, "usage: %s [-h] [-v] [-n]\n", appName);
    fprintf(stdout,
            "  [-i INPUT] [-o OUTPUT] [-s SERVER] [-a ADDRESS] [-k KEY]\n");
    fprintf(stdout, "  {check,list,unpack,pack,update} [dir]\n\n");

    return;
}

void help()
{
    fprintf(stdout, "Operations on Qabel block storage providers\n\n");
    fprintf(stdout, "positional arguments:\n");
    fprintf(stdout, "  {check,list,unpack,pack,update}\n");
    fprintf(stdout, "                        the task to perform\n");
    fprintf(stdout,
            "  dir                   the source or target directory for pack and unpack\n\n");
    fprintf(stdout, "optional arguments:\n");
    fprintf(stdout,
            "  -h, --help            show this help message and exit\n");
    fprintf(stdout, "  -v, --verbose         increase output verbosity\n");
    fprintf(stdout,
            "  -n, --dry-run         do not write any data to disk or network\n");
    fprintf(stdout, "  -i INPUT, --input INPUT\n");
    fprintf(stdout,
            "                        local blocks file to read for unpack/update\n");
    fprintf(stdout, "  -o OUTPUT, --output OUTPUT\n");
    fprintf(stdout,
            "                        local blocks file path to write pack/update\n");
    fprintf(stdout, "  -s SERVER, --server SERVER\n");
    fprintf(stdout, "                        base url for the server\n");
    fprintf(stdout, "  -a ADDRESS, --address ADDRESS\n");
    fprintf(stdout,
            "                        128 bit blocks address in hex (32 bytes) or Base64 (22\n");
    fprintf(stdout, "                        bytes)\n");
    fprintf(stdout,
            "  -k KEY, --key KEY     256 bit AES encryption/decryption key in hex (64\n");
    fprintf(stdout,
            "                        bytes) or Base64 (43 bytes)\n");

    return;
}
