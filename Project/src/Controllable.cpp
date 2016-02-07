#include "Controllable.h"

#include "App.h"

Controllable::Controllable(App* pApp, std::string title)
{
    pApp->registerControllable(this);
    mTitle = title;
}

Controllable::Controllable(std::string title)
{
    mTitle = title;
}


Controllable::~Controllable()
{
    // Nothing to do
}

void Controllable::updateGui()
{
    ImGui::BeginChild("");
    ImGui::TextColored(ImVec4(0,1,0,1), mTitle.c_str());
    fillGui();
    ImGui::EndChild();
}

