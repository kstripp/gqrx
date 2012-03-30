/* -*- c++ -*- */
/*
 * Copyright 2012 K. Scott Tripp.
 *
 * Templated from rx_source_fcd.cpp
 * Copyright 2011 Alexandru Csete OZ9AEC.
 *
 * Gqrx is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * Gqrx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Gqrx; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include <dsp/rx_source_uhd.h>
#include <config.h>

rx_source_uhd_sptr make_rx_source_uhd(const std::string device_name)
{
    return gnuradio::get_initial_sptr(new rx_source_uhd(device_name));
}



rx_source_uhd::rx_source_uhd(const std::string device_name)
    : rx_source_base("rx_source_uhd"),
      d_freq(DEFAULT_FREQ),
      d_gain(DEFAULT_GAIN)
{
    /** TODO: check the uhd_make_usrp_source call **/
	std::string device_addr = "";
/*	const uhd::io_type_t io_type = "fc32";
	size_t numChannels = 1;
*/
	d_uhd_src = uhd_make_usrp_source(uhd::device_addr_t(""), 
			uhd::stream_args_t("fc32"));
    d_uhd_src->set_center_freq(DEFAULT_FREQ);
    d_uhd_src->set_gain((float)DEFAULT_GAIN);

    /** TODO: check error */

    // populate supported sample rates
    d_sample_rates.push_back(96000.0);
	d_sample_rates.push_back(1e+6); //should be possible

    connect(d_uhd_src, 0, self(), 0);
}


rx_source_uhd::~rx_source_uhd()
{

}


void rx_source_uhd::select_device(const std::string device_name)
{
    // The only way to do this for now is to recreate UHD source
    lock();
    disconnect(d_uhd_src, 0, self(), 0);
    d_uhd_src.reset();
	d_uhd_src = uhd_make_usrp_source(uhd::device_addr_t(""), 
			uhd::stream_args_t("fc32"));
    d_uhd_src->set_center_freq((float) d_freq);
    d_uhd_src->set_gain((float) d_gain);
    connect(d_uhd_src, 0, self(), 0);
    unlock();
}

void rx_source_uhd::set_freq(double freq)
{
    if ((freq >= get_freq_min()) && (freq <= get_freq_max())) {
        d_freq = freq;

		/** TODO: make the channel section a variable **/
        d_uhd_src->set_center_freq((float) d_freq, 0);
    }
}

double rx_source_uhd::get_freq()
{
	/** TODO: make channel selection a variable **/
    return d_uhd_src->get_center_freq(0);
}

double rx_source_uhd::get_freq_min()
{
    /** TODO: find a way to get this from get_freq_range() **/
	return 50.0e6;
}

double rx_source_uhd::get_freq_max()
{
    /** TODO: find a way to get this from get_freq_range() **/
    return 2.0e9;
}

void rx_source_uhd::set_gain(double gain)
{
    if ((gain >= get_gain_min()) && (gain <= get_gain_max())) {
        d_gain = gain;

		/** TODO: make channel selection a variable **/
        d_uhd_src->set_gain((float)gain,0);
    }
}

double rx_source_uhd::get_gain()
{
	/** TODO: make channel selection a variable **/
    return d_uhd_src->get_gain(0);
}

double rx_source_uhd::get_gain_min()
{
    // FIXME: magic numbers!!
	return -5.0;
}

double rx_source_uhd::get_gain_max()
{
    // FIXME: magic numbers!!
	return 30.0;
}

void rx_source_uhd::set_sample_rate(double sps)
{
    d_uhd_src->set_samp_rate(sps);
}

double rx_source_uhd::get_sample_rate()
{
    return d_uhd_src->get_samp_rate();
}

std::vector<double> rx_source_uhd::get_sample_rates()
{
    return d_sample_rates;
}

//I don't think UHD supports this
void rx_source_uhd::set_freq_corr(int ppm)
{
    //d_uhd_src->set_freq_corr(ppm);
    // re-tune after frequency correction
    d_uhd_src->set_center_freq((float) d_freq);
}

// TODO: allow for automatic offset correction
// TODO: turn channel number into a variable
void rx_source_uhd::set_dc_corr(double dci, double dcq)
{
	std::complex<double> offset (dci, dcq);
	d_uhd_src->set_dc_offset(offset, 0);
}

// TODO: turn channel number into a variable
void rx_source_uhd::set_iq_corr(double gain, double phase)
{
	std::complex<double> correction(gain, phase);
	d_uhd_src->set_iq_balance(correction, 0);
}
