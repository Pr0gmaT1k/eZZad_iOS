//
//  ClusterView.swift
//  eZZad_iOS
//
//  Created by AzerTy on 13/04/2017.
//  Copyright © 2017 Pr0gmaT1k. All rights reserved.
//

import UIKit
import MapKit
import Reusable

class ClusterView: MKAnnotationView, NibLoadable {
  //
  // Mark:- IBOutlets
  @IBOutlet private weak var subView: UIView!
  
  //
  // Mark:- Public Funcs
  override func awakeFromNib() {
    super.awakeFromNib()
    self.frame = CGRect(x: 0, y: 0, width: 25, height: 25)
  }
  
  override func layoutSubviews() {
    super.layoutSubviews()
    self.layer.cornerRadius = min(self.frame.height, self.frame.width) / 2
    self.subView.layer.cornerRadius = min(self.subView.bounds.height, self.subView.bounds.width) / 2
  }
}
