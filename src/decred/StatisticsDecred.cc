/*
 The MIT License (MIT)

 Copyright (c) [2018] [BTC.COM]

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include "StatisticsDecred.h"
#include "StratumDecred.h"
#include "DecredUtils.h"

template <>
void ShareStatsDay<ShareDecred>::processShare(uint32_t hourIdx, const ShareDecred &share) {
  ScopeLock sl(lock_);

  if (StratumStatus::isAccepted(share.status_)) {
    shareAccept1h_[hourIdx] += share.shareDiff_;
    shareAccept1d_          += share.shareDiff_;

    double score = share.score();
    double reward = GetBlockRewardDecredShare(share.height_, NetworkParamsDecred::get(share.network_));
    double earn = score * reward;

    score1h_[hourIdx] += score;
    score1d_          += score;
    earn1h_[hourIdx]  += earn;
    earn1d_           += earn;

  } else {
    shareReject1h_[hourIdx] += share.shareDiff_;
    shareReject1d_          += share.shareDiff_;
  }
  modifyHoursFlag_ |= (0x01u << hourIdx);
}

///////////////  template instantiation ///////////////
template class ShareStatsDay<ShareDecred>;
