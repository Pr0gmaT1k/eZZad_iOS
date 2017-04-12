//
//  AnnotationView.swift
//  eZZad_iOS
//
//  Created by AzerTy on 13/04/2017.
//  Copyright © 2017 Pr0gmaT1k. All rights reserved.
//

import UIKit
import Reusable
import MapKit

class AnnotationView: MKAnnotationView, NibLoadable {
  override func awakeFromNib() {
    super.awakeFromNib()
    self.frame = CGRect(x: 0, y: 0, width: 22, height: 30)
  }
}
