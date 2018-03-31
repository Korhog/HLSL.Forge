using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Windows.UI;
using Windows.UI.Xaml.Media;


namespace HLSL.Elements
{
    using Base;
    using HLSL.Values;
    using rMind.Elements;
    using rMind.Nodes;

    public class Luminosity : RowContainerBase, IHLSLEditorNode, IHLSLRequireDefine
    {
        public Luminosity(rMindBaseController parent) : base(parent)
        {
            AccentColor = Colors.DarkOrange;

            var output = new Node(this)
            {
                HLSLValueBaseType = Values.HLSLValueBaseType.FLOAT,
                HLSLValueSubType = Values.HLSLValueSubType.NONE,
                Label = "luminosity",
                Stroke = new SolidColorBrush(Colors.DeepSkyBlue),
                UseAccentColor = false,
                ConnectionType = rMindNodeConnectionType.Container,
                NodeOrientation = rMindNodeOriantation.Right,
            };

            AddRow(new rMind.Content.Row.rMindRow
            {
                OutputNode = output,
                InputNodeType = rMind.Nodes.rMindNodeConnectionType.None
            });

            output.Column = 1;
        }

        public override void Init()
        {
            base.Init();
            BorderRadius = new Windows.UI.Xaml.CornerRadius(3);
        }

        public string GetDefineCode()
        {
            return "float luminosity = dot(normalize(float3(-1.0f, 1.0f, 1.0f) - input.world.xyz), input.normal);";
        }

        public HLSLResult GetNodeValue(Node sender)
        {
            return HLSLResult.Result(
                "luminosity",
                sender.HLSLValueBaseType,
                sender.HLSLValueSubType
            );
        }
    }
}
