#coding:utf-8
import pyaudio
import time
import struct
import sys
import wave
import numpy as np
import scipy.fftpack
from pylab import *

#################################
palette = ["r", "g", "b", "c"]

#################################
CHUNK = 1024
FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 48000
RECORD_SECONDS = 1

#################################
SAMPLE_RANGE = 50

#################################
N = 32    # FFTのサンプル数
target_freq = 6000 # 搬送波の周波数
freqList = np.fft.fftfreq(N, d=1.0/RATE)  # 周波数軸の値を計算
def get_nearest_idx(list, num):
    idx = np.abs(np.asarray(list) - num).argmin()
    return idx
target_idx = get_nearest_idx(freqList, target_freq)

code = [[1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0], [1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0], [1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0], [1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0]]

temp_phase = [[np.exp(1.0j * (1 - c) * np.pi) for c in element] for element in code]

code_phase = []
for element in temp_phase:
    temp = []
    for c in element:
        temp.extend(4 * [c])
    code_phase.append(temp)

def plot_ch(corr_abs, ch):
    c = corr_abs[ch]
    plot(range(0, len(c)), c[:], color=palette[ch])
    axis([0, len(corr_abs[0]), array(corr_abs).min(), array(corr_abs).max()])
    xlabel("time [/32 sample]")
    ylabel("correlation ch{}".format(ch))

def get_data(stream):
    x = []
    for i in range(0, int(RATE * RECORD_SECONDS / CHUNK)):
        for j in range(CHUNK):
            b = stream.read(1)
            val = struct.unpack("h", b)[0]
            x.append(val)
    return x

def get_time(x):
    start = 0  # サンプリングする開始位置

    X_time = []


    while start + N < len(x):
        X = np.fft.fft(x[start:start+N])  # FFT
        X_time.append(X[target_idx])
        start += N


    corr = [np.correlate(X_time, c, "valid") for c in code_phase]

    corr_abs = [[np.sqrt(c.real ** 2 + c.imag ** 2) for c in element] for element in corr]

    v = np.array(corr_abs)

    max_tupple = np.unravel_index(v.argmax(), v.shape)
    max_idx = max_tupple[1]
    idx_min = max(0, max_idx - SAMPLE_RANGE)
    idx_max = min(v.shape[1], max_idx + SAMPLE_RANGE + 1)

    peak_idx = []
    for ch in v:
        peak_idx.append(ch[idx_min:idx_max].argmax() + idx_min)

    time = [float(i) * N / RATE for i in peak_idx]
    return time

class calculator:
    """3つのスピーカーからの位相の時間差から，録音機器の位置を推定する"""
    speaker_pos = np.array([])
    sound_velocity = 340.0
    k = 0.01
    epsilon = 0.1
    osc_th = 10
    def __init__(self, speaker_pos):
        self.speaker_pos = np.array(speaker_pos)

    def calc_pos(self, t):
        g1 = self.sound_velocity * (t[1] - t[0])
        g2 = self.sound_velocity * (t[2] - t[0])

        pos = np.array([1.0, 1.0])

        while True:
            diff_F = np.array([[self.diff(pos, 1, 0), self.diff(pos, 1, 1)],
                               [self.diff(pos, 2, 0), self.diff(pos, 2, 1)]])
            P = np.array([g1 - self.calc_gap(pos, 1),
                          g2 - self.calc_gap(pos, 2)])

            dp = np.linalg.inv(diff_F).dot(P)
            pos += self.k * dp
            dp_norm = np.linalg.norm(dp)
            if dp_norm < self.epsilon or dp_norm > self.osc_th:
                break;

        return pos

    def calc_gap(self, pos, i): # スピーカiとスピーカ0の距離の差
        return np.linalg.norm(speaker_pos[i] - pos) - np.linalg.norm(speaker_pos[0] - pos)

    def diff(self, pos, i, j): # i: f_i, j:0のときxで微分，1の時yで微分
        r_0 = self.speaker_pos[0] - pos
        r_i = self.speaker_pos[i] - pos
        return r_0[j] / np.linalg.norm(r_0) - r_i[j] / np.linalg.norm(r_i)

def test_calculator():
    speaker_pos = np.array([[0.0, 0.0],
                            [5.0, 0.0],
                            [0.0, 4.0]])
    calc = calculator(speaker_pos)

    pos = np.array([2.0, 3.6])
    t0 = np.linalg.norm(pos - speaker_pos[0])
    t1 = np.linalg.norm(pos - speaker_pos[1])
    t2 = np.linalg.norm(pos - speaker_pos[2])

    t = np.array([t0, t1, t2])
    print("true pos: {}".format(pos))
    print("ans pos:  {}".format(calc.calc_pos(t)))

def len_to_pos(length):
    pos = []
    pos.append([0.0, 0.0])
    pos.append([length[0], 0.0])
    cos_theta = (length[0] * length[0] + length[2] * length[2] - length[1] * length[1]) / (2 * length[0] * length[2])
    theta = np.arccos(cos_theta)
    x = length[2] * np.cos(theta)
    y = length[2] * np.sin(theta)
    pos.append([x, y])
    return pos


######################################
if __name__ == "__main__" :
    p = pyaudio.PyAudio()
    stream = p.open(format=FORMAT,
                    channels=CHANNELS,
                    rate=RATE,
                    input=True,
                    frames_per_buffer=CHUNK)


    lengths = [5.5, 4.1, 5.5]
    speaker_pos = len_to_pos(lengths)
    calc = calculator(speaker_pos)

    scatter(0, 0)
    temp = 0
    while True:
        x = get_data(stream)
        time = get_time(x)
        pos = calc.calc_pos(time)

        print(time)
        clf()
        subplot(311)
        temp_x = x[0:1000]
        plot(range(0, len(temp_x)), temp_x[:])
        axis([0, len(temp_x), min(temp_x), max(temp_x)])
        xlabel("time [/48000]")
        ylabel("wave")

        subplot(312)
        for i in range(3):
            scatter(speaker_pos[i][0], speaker_pos[i][1], color="r")
        scatter(pos[0], pos[1], color="b")
        pause(0.001)


    # 描画
    subplot(611)  # 3行1列のグラフの1番目の位置にプロット
    plot(range(0, len(amp_time)), amp_time[:])
    axis([0, len(amp_time), min(amp_time), max(amp_time)])
    xlabel("time [/32 sample]")
    ylabel("amplitude")

    subplot(612)  # 3行1列のグラフの1番目の位置にプロット
    plot(range(0, len(phase_time)), phase_time[:])
    axis([0, len(phase_time), min(phase_time), max(phase_time)])
    xlabel("time [/32 sample]")
    ylabel("phase")

    subplot(613)  # 3行1列のグラフの1番目の位置にプロット

    ch = 0
    for c in corr_abs:
        plot(range(0, len(c)), c[:], color=palette[ch])
        ch += 1
    axis([0, len(corr_abs[0]), array(corr_abs).min(), array(corr_abs).max()])
    xlabel("time [/32 sample]")
    ylabel("correlation")

    subplot(614)  # 3行1列のグラフの1番目の位置にプロット
    plot_ch(corr_abs, 0)

    subplot(615)  # 3行1列のグラフの1番目の位置にプロット
    plot_ch(corr_abs, 1)

    subplot(616)  # 3行1列のグラフの1番目の位置にプロット
    plot_ch(corr_abs, 2)

    show()
