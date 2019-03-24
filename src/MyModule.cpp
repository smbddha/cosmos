#include "Cosmos.hpp"

#include "nbody.hpp"

using nbody::Nbody;

struct MyModule : Module {
	enum ParamIds {
		DT_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		VAR0_INPUT,
    VAR1_INPUT,
    VAR2_INPUT,
    VAR3_INPUT,
    VAR4_INPUT,
    NUM_MODS,
    NUM_INPUTS
	};
	enum OutputIds {
		SIN0_OUTPUT,
		SIN1_OUTPUT,
    SIN2_OUTPUT,
    SIN3_OUTPUT,
    SIN4_OUTPUT,
    NUM_OUTPUTS
	};
	enum LightIds {
		BLINK_LIGHT,
		NUM_LIGHTS
	};

	float phase = 0.0;
	float blinkPhase = 0.0;

  float pDt = 100.0;

  float mods[NUM_MODS];

  Nbody nb = Nbody();

	MyModule() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - onReset, onRandomize, onCreate, onDelete: implements special behavior when user clicks these from the context menu

  bool dumbFlag = false; 
};


void MyModule::step() {
	// Implement a simple sine oscillator
	float deltaTime = engineGetSampleTime();

  if (!dumbFlag) {
    nb.parseFile("/home/bdds/projects/vcv/Rack/plugins/cosmos/src/small.txt");
    dumbFlag = true;
    printf("N: %d\n", nb.getN());
  }

  
  for (int i=0; i<NUM_MODS; i++) {
    mods[i] = 0.f;
    if (inputs[(InputIds) i].active) 
      mods[i] = inputs[(InputIds) i].value * (nb.get(1,i+1) * 0.1f);
  }
  

  float dt = params[DT_PARAM].value;
  if (pDt != dt) nb.setDt(dt);

	// Compute the sine output
  float sig0,sig1,sig2,sig3,sig4;
  sig0 = nb.get(1,1) + mods[0];
  sig1 = nb.get(1,2) + mods[1];
  sig2 = nb.get(1,3) + mods[2];
  sig3 = nb.get(1,4) + mods[3];
  sig4 = nb.get(1,5) + mods[4];

	outputs[SIN0_OUTPUT].value = 5.0f * sig0;
  outputs[SIN1_OUTPUT].value = 5.0f * sig1;
  outputs[SIN2_OUTPUT].value = 5.0f * sig2;
  outputs[SIN3_OUTPUT].value = 5.0f * sig3;
  outputs[SIN4_OUTPUT].value = 5.0f * sig4;

  // Blink light at 1Hz
	blinkPhase += deltaTime;
	if (blinkPhase >= 1.0f)
		blinkPhase -= 1.0f;
	lights[BLINK_LIGHT].value = (blinkPhase < 0.5f) ? 1.0f : 0.0f;

  nb.step();
}


struct MyModuleWidget : ModuleWidget {
	MyModuleWidget(MyModule *module) : ModuleWidget(module) {
		setPanel(SVG::load(assetPlugin(plugin, "res/CosmosPanel.svg")));

		addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(ParamWidget::create<Davies1900hBlackKnob>(Vec(28, 87), module, MyModule::DT_PARAM, 100.0, 10000.0, 0.0));

		addInput(Port::create<PJ301MPort>(Vec(55, 255), Port::INPUT, module, MyModule::VAR0_INPUT));
    addInput(Port::create<PJ301MPort>(Vec(90, 255), Port::INPUT, module, MyModule::VAR1_INPUT));
    addInput(Port::create<PJ301MPort>(Vec(125, 255), Port::INPUT, module, MyModule::VAR2_INPUT));
    addInput(Port::create<PJ301MPort>(Vec(160, 255), Port::INPUT, module, MyModule::VAR3_INPUT));
    addInput(Port::create<PJ301MPort>(Vec(195, 255), Port::INPUT, module, MyModule::VAR4_INPUT));

		addOutput(Port::create<PJ301MPort>(Vec(55, 294.6), Port::OUTPUT, module, MyModule::SIN0_OUTPUT));
    addOutput(Port::create<PJ301MPort>(Vec(90, 294.6), Port::OUTPUT, module, MyModule::SIN1_OUTPUT));
    addOutput(Port::create<PJ301MPort>(Vec(125, 294.6), Port::OUTPUT, module, MyModule::SIN2_OUTPUT));
    addOutput(Port::create<PJ301MPort>(Vec(160, 294.6), Port::OUTPUT, module, MyModule::SIN3_OUTPUT));
    addOutput(Port::create<PJ301MPort>(Vec(195, 294.6), Port::OUTPUT, module, MyModule::SIN4_OUTPUT));


		addChild(ModuleLightWidget::create<MediumLight<RedLight>>(Vec(41, 59), module, MyModule::BLINK_LIGHT));
	}
};


// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelMyModule = Model::create<MyModule, MyModuleWidget>("Cosmos", "Cosmos Osc", "A cosmos osc", OSCILLATOR_TAG);
