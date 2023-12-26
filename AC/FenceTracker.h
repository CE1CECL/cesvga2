/*

    CEsvga2 - ChrisEric1 Super Video Graphics Array 2
    Copyright (C) 2023-2024, Christopher Eric Lentocha

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#ifndef __FENCETRACKER_H__
#define __FENCETRACKER_H__

template<size_t N>
struct FenceTracker
{
	size_t counter;
	unsigned fences[N];

	void init()
	{
		counter = 0;
		bzero(&fences, sizeof fences);
	}

	unsigned before()
	{
		return fences[counter];
	}

	void after(unsigned fence)
	{
		fences[counter] = fence;
		++counter;
		if (counter == N)
			counter = 0;
	}
};

#endif /* __FENCETRACKER_H__ */
