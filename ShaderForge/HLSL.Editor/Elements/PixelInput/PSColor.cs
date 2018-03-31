using Windows.UI;
using Windows.UI.Xaml.Media;

namespace HLSL.Elements
{
    using Base;

    using rMind.Nodes;
    using rMind.Elements;
    using HLSL.Values;

    public class PSColor : RowContainerBase, IHLSLEditorNode
    {
        Node output;

        public PSColor(rMindBaseController parent) : base(parent)
        {
            AccentColor = Colors.LimeGreen;

            output = new Node(this)
            {
                HLSLValueBaseType = Values.HLSLValueBaseType.FLOAT3,
                Label = "ps input :: color",
                Stroke = new SolidColorBrush(Colors.MediumVioletRed),
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

        public HLSLResult GetNodeValue(Node sender)
        {
            return HLSLResult.Result("input.color", sender.HLSLValueBaseType);
        }
    }
}
