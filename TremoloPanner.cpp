bool __stdcall CTremoloPanner::processAudioFrame(float* pInputBuffer, float* pOutputBuffer, UINT uNumInputChannels, UINT uNumOutputChannels)
{
	// Do LEFT (MONO) Channel; there is always at least one input/one output
	float fYn = 0; // normal output
	float fYqn = 0; // quad phase output

	// call the LFO function; we only need first output
	m_LFO.doOscillate(&fYn, &fYqn);

	// setup necessary variables
	float fGnL = 1.0;
	float fGnR = 1.0;
	float fMonoIn = 0.0;

	// branch
	if (m_uMode == Tremolo)
	{
		fGnL = calculateGainFactor(fYn);
	}
	else // panner sums inputs
	{
		if (uNumInputChannels == 1)
		{
			fMonoIn = pInputBuffer[0];
		}
		else
		{
			fMonoIn = 0.5*(pInputBuffer[0] + pInputBuffer[1]);
		}
		calculatePannerGainFactor(fYn, &fGnL, &fGnR);
	}

	//do MONO (Left) channel
	pOutputBuffer[0] = pInputBuffer[0] * fGnL;

	// Mono-In, Stereo-Out (AUX Effect)
	if (uNumInputChannels == 1 && uNumOutputChannels == 2)
		pOutputBuffer[1] = pInputBuffer[0]; // just copy

	// Stereo-In, Stereo-Out (INSERT Effect)
	if (uNumInputChannels == 2 && uNumOutputChannels == 2)
	{
		// branch
		if (m_uMode == Tremolo)
		{
			// do right channel, use same gain as left
			pOutputBuffer[1] = pInputBuffer[1] * fGnL;
		}
		else
		{
			// do right channel, its value
			pOutputBuffer[1] = pInputBuffer[1] * fGnR;
		}

	}
	return true;
}
