using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HLSL.Elements
{
    using Base;
    using HLSL.Values;
    using rMind.Content.Row;
    using rMind.Elements;
    using rMind.Nodes;
    using Windows.UI;
    using Windows.UI.Xaml.Media;

    public class Vector3Node : RowContainerBase, IHLSLEditorNode
    {
        public Vector3Node(rMindBaseController parent) : base(parent)
        {
            AccentColor = Colors.DarkBlue;
            // Green
            AddRow(new rMindRow
            {
                InputNodeType = rMindNodeConnectionType.None,
                OutputNode = new Node(this)
                {
                    HLSLValueBaseType = HLSLValueBaseType.FLOAT3,
                    UseAccentColor = false,
                    IDS = "vector",
                    Label = "vector3",
                    ConnectionType = rMindNodeConnectionType.Container,
                    NodeOrientation = rMindNodeOriantation.Right,
                    Stroke = new SolidColorBrush(Colors.Green)
                }
            });
            AddSeparator();
            // x | r
            AddRow(new rMindRow
            {
                InputNodeType = rMindNodeConnectionType.None,
                OutputNode = new Node(this)
                {
                    HLSLValueBaseType = HLSLValueBaseType.FLOAT,
                    HLSLValueSubType = HLSLValueSubType.X_R,
                    UseAccentColor = false,
                    IDS = "X",
                    Label = "X",
                    ConnectionType = rMindNodeConnectionType.Container,
                    NodeOrientation = rMindNodeOriantation.Right,
                    Stroke = new SolidColorBrush(Colors.IndianRed)
                }
            });
            // y | g
            AddRow(new rMindRow
            {
                InputNodeType = rMindNodeConnectionType.None,
                OutputNode = new Node(this)
                {
                    HLSLValueBaseType = HLSLValueBaseType.FLOAT,
                    HLSLValueSubType = HLSLValueSubType.Y_G,
                    UseAccentColor = false,
                    IDS = "Y",
                    Label = "Y",
                    ConnectionType = rMindNodeConnectionType.Container,
                    NodeOrientation = rMindNodeOriantation.Right,
                    Stroke = new SolidColorBrush(Colors.Green)
                }
            });
            // z | b
            AddRow(new rMindRow
            {
                InputNodeType = rMindNodeConnectionType.None,
                OutputNode = new Node(this)
                {
                    HLSLValueBaseType = HLSLValueBaseType.FLOAT,
                    HLSLValueSubType = HLSLValueSubType.Z_B,
                    UseAccentColor = false,
                    IDS = "Z",
                    Label = "Z",
                    ConnectionType = rMindNodeConnectionType.Container,
                    NodeOrientation = rMindNodeOriantation.Right,
                    Stroke = new SolidColorBrush(Colors.DeepSkyBlue)
                }
            });
        }

        public HLSLResult GetNodeValue(Node sender)
        {
            throw new NotImplementedException();
        }
    }
}
