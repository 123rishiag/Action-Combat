// Action Combat

using UnrealBuildTool;
using System.Collections.Generic;

public class ActionCombatEditorTarget : TargetRules
{
	public ActionCombatEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "ActionCombat" } );
	}
}
