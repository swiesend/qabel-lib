/*
 * @file    	qbl-keygen.h
 * @brief       Main file to generate keys (header file)
 * @author    	Enno Boland <boland@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include <vector>

std::vector<char> qblKeyGenAes256();

std::vector<char> qblKeyGenAes256IV();

std::vector<char> qblKeyGenRsa();
